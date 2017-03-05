<?php

function conversational_forms_webform_component_render_alter(&$element, &$component) {
	$element['#attributes'] = array(
		  'cf-questions' => $component['extra']['cf-questions'],
		  'cf-error' => $component['extra']['cf-error'],
		  'pattern' => $component['extra']['cf-pattern'],
		);
  // print_r('<pre>'); print_r($component); die();
	if ($component['required']) {
		$element['#attributes']['required'] = 'required';
	}
}

function conversational_forms_webform_component_defaults_alter(&$defaults, $type) {

  // Add a default for a new field added via hook_form_alter() or
  // hook_form_FORM_ID_alter() for all component types.
  $defaults['extra']['cf-questions'] = '';
  $defaults['extra']['cf-error'] = '';
  $defaults['extra']['cf-pattern'] = '';
  $defaults['extra']['cf-add-to-webform'] = '';

}

function conversational_forms_form_webform_component_edit_form_alter(&$form, &$form_state) {
	// print_r('<pre>'); print_r($form['#node']->webform['components'][$form['cid']['#value']]['type']); die();
	$pattern = $form['#node']->webform['components'][$form['cid']['#value']]['extra']['cf-pattern'];
	if (empty($pattern)) {
		switch ($form['#node']->webform['components'][$form['cid']['#value']]['type']) {
			case 'date':
				// @TODO
				break;
			case 'email':
			    // @TODO
				break;
			case 'number':
				// @TODO
				break;
			case 'time':
				// @TODO
				break;
		}
	}
	$cf_add = conversational_forms_is_enabled($form['#node']->nid);
	if (!$cf_add) {
		return;
	}
	$form['extra']['cf-questions'] = array(
	  '#type' => 'textarea',
	  '#title' => t('CF Questions'),
	  '#default_value' => $form['#node']->webform['components'][$form['cid']['#value']]['extra']['cf-questions'], //@TODO: see better way to fetch this value.
	  '#description' => t("<p>If specified, this question will be presented to the user instead of the label.</p>Use <i>{previous-answer}</i> to print the user submitted value of previous field. Multiple errors can be defined to be presented randomly using a pipe e.g. <em>Error1|Error2|Error</em>"),
	);
	$form['extra']['cf-error'] = array(
	  '#type' => 'textarea',
	  '#title' => t('CF Error'),
	  '#default_value' => $form['#node']->webform['components'][$form['cid']['#value']]['extra']['cf-error'], //@TODO: see better way to fetch this value.
	  '#description' => t("<p>Configure the error message in case there is incorrect input.</p>Multiple errors can be defined to be asked randomly using a pipe e.g. <em>Question1|Question2|Question3</em>"),
	);
	$form['extra']['cf-pattern'] = array(
	  '#type' => 'textarea',
	  '#title' => t('CF Pattern'),
	  '#default_value' => $pattern,
	  '#description' => t('!regex for field validation.', array('!regex' => l('Regex', 'http://www.html5pattern.com', array('attributes' => array('target'=>'_blank'))))),
	);
}
